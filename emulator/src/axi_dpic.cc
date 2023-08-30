#include "svdpi.h"

extern "C" void AXI4BFMDPI(
    const svBitVecVal* arid,
    const svBitVecVal* araddr,
    const svBitVecVal* arlen,
    const svBitVecVal* arsize,
    const svBitVecVal* arburst,
    svLogic arvalid,
    svLogic* arready,
    svBitVecVal* rid,
    svBitVecVal* rdata,
    svLogic* rlast,
    svBitVecVal* rresp,
    svLogic* rvalid,
    svLogic rready,
    const svBitVecVal* awid,
    const svBitVecVal* awaddr,
    const svBitVecVal* awlen,
    const svBitVecVal* awsize,
    const svBitVecVal* awburst,
    svLogic awvalid,
    svLogic* awready,
    const svBitVecVal* wdata,
    svLogic wlast,
    const svBitVecVal* wstrb,
    svLogic wvalid,
    svLogic* wready,
    svBitVecVal* bid,
    svBitVecVal* bresp,
    svLogic* bvalid,
    svLogic bready) {

}