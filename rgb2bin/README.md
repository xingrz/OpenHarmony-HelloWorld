rgb2bin
======

Convert RGB888 raw bitmap to pixel array used by RETRPL.

## Build

```
mkdir -p out && pushd out && cmake .. && make -j4 && popd
```

## Use

```
ffmpeg -i input.png -f rawvideo -pix_fmt rgb24 - | out/rgb2bin output.bin
```
