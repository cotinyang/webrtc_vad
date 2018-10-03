# WebRTC VAD
Voice activity detection (VAD) library, extract from WebRTC.

This repository just contains the scripts to build VAD library from WebRTC source code.  
And WebRTC is a submodule of this repository.

## Building

1. Get WebRTC source code
```
git submodule update --recursive --remote
```
2. Build with cmake
```
mkdir build
cmake ..
make
```

## Usage
Copy the output files to your own project.

Files in output dir: build/webrtc_vad

```
.
├── include
│   ├── vad.h
│   └── webrtc_vad.h
├── lib
│   └── libwebrtc_vad.so
```
