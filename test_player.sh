!#/bin/bash

function print_seperator() {
    echo "===================================================="
}

for audio_file in sample_wave_files/*.wav;do
    echo "[INFO]: Playing file" $audio_file
    ./pulse_player $audio_file
    print_seperator
done

echo "All tests passed"