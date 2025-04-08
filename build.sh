echo "============================================"
echo "|          CobaltOS Build Script           |"
echo "============================================"

echo -n "Configuring via CMake..."
mkdir -p build build/cobalt
if ! cmake -B build -S . >build/config-output.log 2>&1 1>/dev/null; then
    echo ""
    echo "CMake failed to configure. Please see the build/config-output.log file."
    exit 255
fi
echo "done."
echo "     See the build/config-output.log for any messages/warnings."

echo -n "Creating boot stub..."
nasm -f bin -o build/cobalt/bootstub Bootloader.asm
echo "done."

echo -n "Compiling and linking..."
cd build

if ! cmake --build . --parallel 9 >compile-output.log 2>&1 1>/dev/null; then
    echo ""
    echo "CMake failed to build. Please see the build/compile-output.log file."
    exit 255
fi
echo "done."

echo -n "Creating disk image..."
# 128MB disk image
dd if=/dev/zero of=cobalt/cobalt.iso bs=1048576 count=128 status=none
dd if=cobalt/bootstub of=cobalt/cobalt.iso conv=notrunc bs=446 count=1 status=none
dd if=cobalt/bootstub of=cobalt/cobalt.iso conv=notrunc bs=1 count=2 skip=510 seek=510 status=none
echo "done."

echo "To run:"
echo "     qemu-system-x86_64 -drive format=raw,file=./build/cobalt/cobalt.iso"

echo "Thank you."