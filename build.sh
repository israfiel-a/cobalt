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
nasm -f bin -o build/cobalt/bootstub Bootloader/Root.asm
echo "done."

echo -n "Compiling and linking..."
cd build

if ! cmake --build . --parallel 9 >compile-output.log 2>&1 1>/dev/null; then
    echo ""
    echo "CMake failed to build. Please see the build/compile-output.log file."
    exit 255
fi
echo "done."

echo "Thank you."