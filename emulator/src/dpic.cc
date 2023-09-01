#include "svdpi.h"
#include "VTestHarness__Dpi.h"
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <csignal>
#include "mmio_mem.hpp"
#include "axi4_xbar.hpp"

#define DPI extern "C"
#define IN const
#define OUT

mmio_mem ram(0x20000000);
axi4_xbar<30,32,4> mem_xbar;
axi4     <30,32,4> mem_sigs;
axi4_ref <30,32,4> mem_sigs_ref(mem_sigs);

DPI void init_cosim() {
    // init dumpwave
    svSetScope(svGetScopeFromName("TOP.TestHarness.dpiDumpWave"));
    dump_wave("trace.fst");
    // sigint signal
    std::signal(SIGINT, [](int) {
        svSetScope(svGetScopeFromName("TOP.TestHarness.dpiFinish"));
        finish();
    });
    // setup soc
    assert(mem_xbar.add_dev(0x20000000, 0x20000000, &ram));
    // load workload
    ram.load_binary(0, "workload/memory_loop/bootrom.img");
}

    
extern "C" void AXI4BFMDPI(
    IN  svBitVecVal* arid,
    IN  svBitVecVal* araddr,
    IN  svBitVecVal* arlen,
    IN  svBitVecVal* arsize,
    IN  svBitVecVal* arburst,
    IN  svLogic arvalid,
    OUT svLogic* arready,
    OUT svBitVecVal* rid,
    OUT svBitVecVal* rdata,
    OUT svLogic* rlast,
    OUT svBitVecVal* rresp,
    OUT svLogic* rvalid,
    IN  svLogic rready,
    IN  svBitVecVal* awid,
    IN  svBitVecVal* awaddr,
    IN  svBitVecVal* awlen,
    IN  svBitVecVal* awsize,
    IN  svBitVecVal* awburst,
    IN  svLogic awvalid,
    OUT svLogic* awready,
    IN  svBitVecVal* wdata,
    IN  svLogic wlast,
    IN  svBitVecVal* wstrb,
    IN  svLogic wvalid,
    OUT svLogic* wready,
    OUT svBitVecVal* bid,
    OUT svBitVecVal* bresp,
    OUT svLogic* bvalid,
    IN  svLogic bready) {

    // CTRL START {
    mem_xbar.beat(mem_sigs_ref);
    // CTRL  END  }
    
    // output ar
    *arready = mem_sigs.arready;

    // output r
    *rid    = mem_sigs.rid;
    *rdata  = mem_sigs.rdata;
    *rlast  = mem_sigs.rlast;
    *rresp  = mem_sigs.rresp;
    *rvalid = mem_sigs.rvalid;

    // output aw
    *awready= mem_sigs.awready;

    // output w
    *wready = mem_sigs.wready;

    // output b
    *bid    = mem_sigs.bid;
    *bresp  = mem_sigs.bresp;
    *bvalid = mem_sigs.bvalid;

    // input ar
    mem_sigs.arid   = *arid;
    mem_sigs.araddr = *araddr;
    mem_sigs.arlen  = *arlen;
    mem_sigs.arsize = *arsize;
    mem_sigs.arburst= *arburst;
    mem_sigs.arvalid= arvalid;

    // input r
    mem_sigs.rready = rready;

    // input aw
    mem_sigs.awid   = *awid;
    mem_sigs.awaddr = *awaddr;
    mem_sigs.awlen  = *awlen;
    mem_sigs.awsize = *awsize;
    mem_sigs.awburst= *awburst;
    mem_sigs.awvalid= awvalid;

    // input w
    mem_sigs.wdata  = *wdata;
    mem_sigs.wstrb  = *wstrb;
    mem_sigs.wlast  = wlast;
    mem_sigs.wvalid = wvalid;
    
    // input b
    mem_sigs.bready = bready;
}