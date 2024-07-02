#
# Copyright (C) 2017-2023 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#
# rev-xbgas-test.py
#

# ---------------------------------------------------------------
#
#  xbgas_host0           xbgas_host1
#      |                     |
#  rmt_mem_ctrl0        rmt_mem_ctrl1    
#      |                     |  
#     nic0                  nic1
#      |                     |
#    iface0 <-> router <-> iface1
#                  |
#               topology
#
#   <-> is a link
#   | is a subcomponent relationship

import os
import sst
import sys

# Define SST core options
sst.setProgramOption("timebase", "1ps")

# Tell SST what statistics handling we want
# sst.setStatisticLoadLevel(1)

if len(sys.argv) != 2:
  sys.stderr.write("Usage: You must pass the number of PEs using the '--model-options' option with sst\n")
  raise SystemExit(1)

NPES = sys.argv[1]
PROGRAM = "gups.exe"

CLOCK = "2.5GHz"  
MEMSIZE = 1024*1024*1024
SHARED_MEM_SIZE = 1024*1024*256

memctrl_params = {
  "clock": CLOCK,
  "addr_range_start": 0,
  "addr_range_end": MEMSIZE-1,
  "backing": "malloc"
}

mem_params = {
  "access_time" : "100ns",
  "mem_size" : "8GB"
}

net_params = {
  "input_buf_size" : "512B",
  "output_buf_size" : "512B",
  "link_bw" : "10GB/s"
}

# setup the router
router = sst.Component("router", "merlin.hr_router")
router.setSubComponent("topology", "merlin.singlerouter")
router.addParams(net_params)

router.addParams({
    "xbar_bw" : "10GB/s",
    "flit_size" : "32B",
    "num_ports" : NPES,
    "id" : 0
})

for i in range(0, int(NPES)):
  if i == 0:
    VERBOSE = 1
    SPLASH = 0
  else:
    VERBOSE = 1
    SPLASH = 0
  # xBGAS CPUs
  xbgas_cpu = sst.Component("cpu" + str(i), "revcpu.RevCPU")
  xbgas_cpu.addParams({
    "verbose" : VERBOSE,                          # Verbosity
    "clock" : CLOCK,                              # Clock
    "program" : os.getenv("REV_EXE", PROGRAM),    # Target executable
    "memSize" : MEMSIZE,                          # Memory size in bytes
    "startAddr" : "[0:0x00000000]",               # Starting address for core 0
    "machine" : "[0:RV64GCX]",
    "memCost" : "[0:1:10]",                       # Memory loads required 1-10 cycles
    "enable_xbgas" : 1,                           # Enable XBGAS support 
    "enable_memH": 1,                             # Enable memHierarchy support
    "shared_memory_size": SHARED_MEM_SIZE,        # Shared memory size
    "splash" : SPLASH                                  # Display the splash message
  })
  # print("Created xBGAS CPU component " + str(i) + ": " + xbgas_cpu.getFullName())
  
  xbgas_cpu.enableAllStatistics()
  
  # Setup the memory controllers
  lsq = xbgas_cpu.setSubComponent("memory", "revcpu.RevBasicMemCtrl")

  # Create the memHierarchy subcomponent
  miface = lsq.setSubComponent("memIface", "memHierarchy.standardInterface")
  
  # Create the memory controller in memHierarchy
  memctrl = sst.Component("memory" + str(i), "memHierarchy.MemController")
  memctrl.addParams(memctrl_params)

  # Create the memory backend subcomponent
  memory = memctrl.setSubComponent("backend", "memHierarchy.simpleMem")
  memory.addParams(mem_params)
  
  # setup the links
  link_miface_mem = sst.Link("link_miface_mem" + str(i))
  link_miface_mem.connect( (miface, "port", "50ps"), (memctrl, "direct_link", "50ps") )
  
  # Create remote memory controllers
  rmt_lsq = xbgas_cpu.setSubComponent("remote_memory", "revcpu.RevBasicRmtMemCtrl")
  rmt_nic = rmt_lsq.setSubComponent("xbgasNicIface", "revcpu.XbgasNIC")
  rmt_nic_iface = rmt_nic.setSubComponent("iface", "merlin.linkcontrol")

  rmt_nic_iface.addParams(net_params)
  
  # Setup the links
  link = sst.Link("link" + str(i))
  link.connect( (rmt_nic_iface, "rtr_port", "20ns"), (router, f"port{i}", "20ns") )


# # Tell SST what statistics handling we want
# sst.setStatisticOutput("sst.statOutputCSV")
# sst.enableAllStatisticsForAllComponents()

# EOF
