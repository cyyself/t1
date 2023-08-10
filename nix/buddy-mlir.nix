{ stdenv, cmake, ninja, python3, fetchFromGitHub }:

stdenv.mkDerivation rec {
  pname = "buddy-mlir";
  version = "unstable-2023-05-26";
  srcs = [
    (fetchFromGitHub {
      owner = "buddy-compiler";
      repo = "buddy-mlir";
      rev = "05f9099740dc1f9dbea6bb828bc1cae1de618be5";
      sha256 = "sha256-/xI4agRpdmAgWjRayk+qcG6F/L5/6alYJxtrS8NTKA0=";
    })

    (fetchFromGitHub {
      owner = "llvm";
      repo = "llvm-project";
      rev = "8f966cedea594d9a91e585e88a80a42c04049e6c";
      sha256 = "sha256-g2cYk3/iyUvmIG0QCQpYmWj4L2H4znx9KbuA5TvIjrc=";
    })
  ];
  sourceRoot = ".";
  unpackPhase = ''
    sources=($srcs)
    # [0] buddy-mlir
    cp -rT ''${sources[0]} buddy-mlir
    # sources are copy from RO store
    chmod -R u+w -- buddy-mlir
    # [1] llvm: cmake is hard-coded to find llvm inside buddy-mlir
    cp -rT ''${sources[1]} buddy-mlir/llvm
    chmod -R u+w -- buddy-mlir/llvm
  '';
  # Bash variable is not resolved in cmakeFlags
  preConfigure = ''
    cmakeFlagsArray+=(
      -DLLVM_EXTERNAL_BUDDY_MLIR_SOURCE_DIR="$(realpath buddy-mlir)"
    )
  '';

  requiredSystemFeatures = [ "big-parallel" ];

  nativeBuildInputs = [ cmake ninja python3 ];

  # CMakeList is available in llvm main source inside the llvm repo
  cmakeDir = "../buddy-mlir/llvm/llvm";
  cmakeFlags = [
    "-DLLVM_ENABLE_BINDINGS=OFF"
    "-DLLVM_ENABLE_OCAMLDOC=OFF"
    "-DLLVM_BUILD_EXAMPLES=OFF"
    "-DLLVM_ENABLE_PROJECTS=mlir;clang"
    "-DLLVM_TARGETS_TO_BUILD=host;RISCV"
    "-DLLVM_INSTALL_UTILS=ON"
    "-DLLVM_ENABLE_ASSERTIONS=ON"
    "-DLLVM_EXTERNAL_PROJECTS=${pname}"
  ];

  checkTarget = "check-mlir check-clang check-buddy";
}
