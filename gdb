#!/usr/bin/env bash
# Starts a GDB session on CSGO,
# Sets a couple of things up and then you can use GDB normally

function echo_red {
	echo -e "\e[31m$*\e[0m"
}

csgo_pid=$(pidof CheatersCheetah)
if [ -z "$csgo_pid" ]; then
    echo_red "CS:GO needs to be open..."
    exit 1
fi

#https://www.kernel.org/doc/Documentation/security/Yama.txt
echo "2" | sudo tee /proc/sys/kernel/yama/ptrace_scope # Only allows root to inject code. This is temp until reboot.


echo "CSGO PID: " $csgo_pid
sudo gdb \
-ex "handle SIGUSR1 nostop noprint pass" \
-p $csgo_pid
