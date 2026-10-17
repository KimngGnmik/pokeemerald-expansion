#!/bin/zsh
cd "$HOME/Documents/gamedev/pokemon/pokeemerald-expansion" || exit 1
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
echo "Building..."
if make -j$(sysctl -n hw.ncpu); then
  echo "Build OK, launching game."
  open -a mGBA pokeemerald.gba
else
  echo "BUILD FAILED - scroll up for the error."
  read -k1 "?Press any key to close."
fi
