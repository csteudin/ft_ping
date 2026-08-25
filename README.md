# ft_ping by csteudin

### A from-scratch reimplementation of the `ping` command in C

*Raw sockets. Raw packet. Raw `ping`.*


## Table of Contents

- [What is this?](#what-is-this)
- [How ping actually works](#how-ping-actually-works)
- [Build & Run](#build--run)
- [Mandatory features](#mandatory-features)
- [Bonus features](#bonus-features)
- [Output showcase](#output-showcase)
- [Project structure](#project-structure)
- [Resources](#resources)

---

## What is this?

`ft_ping` is a personal reimplementation of the classic `ping` command from **[inetutils-2.0](https://www.gnu.org/software/inetutils/)**, built for the 42 curriculum.

`ping` answers one simple question:

> **"Is this other machine on the network actually alive and reachable?"**

It sends small network messages to a target and waits to see if they come back. If they do, the target is alive — and `ping` also tells you *how long* the round trip took.

This project builds that mechanism **entirely from scratch** in C: raw sockets, hand-crafted packets, manual checksums, no libraries doing the networking for you, and no calling the real system `ping` under the hood.

---

## How ping actually works

No prior networking knowledge needed — here's the whole idea in plain terms:

1. Your computer builds a tiny message called an **ICMP Echo Request** (nicknamed a "ping").
2. It stamps the current time inside that message and sends it to the target.
3. If the target is alive, it sends the exact same message straight back — an **Echo Reply**.
4. Your computer receives it, checks the timestamp again, and calculates how long the round trip took: the **RTT (Round-Trip Time)**.
5. Repeat this every second (or however often you like), and print a summary at the end.

That's it — two tiny protocols working together:

| Protocol | Role in this project |
|---|---|
| **IP** ([RFC 791](https://datatracker.ietf.org/doc/html/rfc791)) | Gets the packet from A to B across the network |
| **ICMP** ([RFC 792](https://datatracker.ietf.org/doc/html/rfc792)) | The "ping"/"pong" message format itself |

The core loop, in pseudocode:

```
initialize()
parse(argv)                 -> host, flags
resolve(host)                -> destination IP
open_raw_socket()
set_socket_options(ttl, tos, dontroute)

print("PING <host> (<ip>): <n> data bytes")

loop until count reached (or forever):
    build_icmp_echo_request(sequence, timestamp = now())
    send(packet)

    if reply arrives before timeout:
        verify(reply)                         # type, code, id, checksum
        rtt = now() - timestamp_from(reply)
        update_stats(rtt)
        print("<n> bytes from <ip>: icmp_seq=<x> ttl=<y> time=<rtt> ms")
    else:
        print("Request timeout") if verbose

    sleep(interval - time_already_spent_waiting)

on exit (Ctrl+C or count reached):
    print_statistics()   # transmitted, received, loss %, rtt min/avg/max
    close(socket)
```

---

## Build & Run

```bash
make
sudo ./ft_ping <host>
```

> [!IMPORTANT]
> `sudo` is required. Building a raw ICMP socket is a privileged operation — the kernel doesn't let random processes forge network packets, for obvious security reasons.

```bash
sudo ./ft_ping google.com
sudo ./ft_ping 1.1.1.1
sudo ./ft_ping -v -c 4 -i 0.5 google.com
```

---

## Mandatory features

| Flag | What it does |
|---|---|
| `-v` | **Verbose mode.** Shows extra detail about rejected/unexpected packets instead of silently ignoring them — useful for debugging or understanding *why* something didn't work. |
| `-?` | **Help.** Prints usage information and exits immediately. |

Beyond the flags, the mandatory part covers:
- Resolving a hostname (e.g. `google.com`) **or** a plain IPv4 address as the target
- Sending real ICMP Echo Requests over a raw socket
- Printing one line per reply, with byte count, source IP, sequence number, TTL, and round-trip time
- A clean statistics summary on exit (via `Ctrl+C` or after a fixed count) — packets sent, received, loss %, and min/avg/max RTT
- No crashes, ever — every syscall failure is caught and reported cleanly instead of segfaulting

</div>

---

## Bonus features

| Flag | Argument | Purpose |
|---|---|---|
| `-c` | `<count>` | stop after sending a fixed number of packets |
| `-i` | `<seconds>` | set the interval between packets |
| `--ttl` | `<n>` | set the packet's Time-To-Live |
| `-T` | `<num>` | set the packet's Type of Service (TOS) |
| `-r` | — | bypass routing, send directly on the local network |

Each one solves a real, specific problem you'd actually run into when debugging a network.

### `-c <count>` — send a fixed number of packets
**Problem it solves:** by default, `ping` runs forever until you hit `Ctrl+C`. That's inconvenient for scripts or quick one-off checks. `-c 4` sends exactly 4 packets and stops automatically, printing the stats right after.

```bash
sudo ./ft_ping -c 4 google.com
```

### `-i <seconds>` — control the interval between packets
**Problem it solves:** the default 1-second gap between pings isn't always right — sometimes you want a faster burst to stress-test a connection, sometimes a slower pace to avoid flooding a fragile link.

```bash
sudo ./ft_ping -i 0.3 google.com
```

### `--ttl <n>` — control the packet's Time-To-Live
**Problem it solves:** every packet on the internet carries a TTL — a countdown that drops by 1 at every router it passes through. When it hits 0, the packet dies and the router that killed it sends back a notice. This is normally invisible to you.

Setting a low TTL on purpose lets you find out how many network hops away a target actually is, or intentionally trigger a "died along the way" response to test how your program handles unusual replies.

```bash
sudo ./ft_ping --ttl 1 google.com
```

### `-T <num>` — set the Type of Service (TOS)
**Problem it solves:** TOS is a small tag inside every IP packet meant to hint "please prioritize this traffic" to routers that support it (e.g. voice calls vs. background downloads). It's mostly invisible on the regular internet, but it's a real, standard knob network engineers use — and a standard `ping` flag to expose it.

```bash
sudo ./ft_ping -T 16 google.com
```

### `-r` — bypass routing, send directly on the local network
**Problem it solves:** normally, your OS decides how to reach a target by consulting its routing table. If that table is broken or missing an entry — but the target is still physically sitting on the same local network — you can force the packet out directly, skipping the routing decision entirely.

```bash
sudo ./ft_ping -r 192.168.1.42
```



</div>

---

## Output showcase
</div>

```
PING google.com (142.250.74.206): 56 data bytes
64 bytes from 142.250.74.206: icmp_seq=0 ttl=115 time=11.203 ms
64 bytes from 142.250.74.206: icmp_seq=1 ttl=115 time=10.877 ms
64 bytes from 142.250.74.206: icmp_seq=2 ttl=115 time=11.502 ms
64 bytes from 142.250.74.206: icmp_seq=3 ttl=115 time=10.994 ms

--- google.com ping statistics ---
4 packets transmitted, 4 received, 0% packet loss
rtt min/avg/max = 10.877/11.144/11.502 ms
```

---

## Project structure

```
ft_ping/
├── inc/
│   └── ping.h            # shared types, prototypes, t_ping struct
├── src/
│   ├── main.c            # entry point + main send/receive loop
│   ├── parcing.c         # argv parsing, flag handling, packet validation
│   ├── socket.c          # raw socket setup, host resolution
│   ├── connection.c      # checksum, send/receive, timeout handling
│   ├── signals.c         # Ctrl+C handling
│   ├── print.c           # all user-facing output (help, banner, stats)
│   └── utils.c           # small helpers (number/float validation, error exit)
└── Makefile
```

---

## Resources

- https://datatracker.ietf.org/doc/html/rfc791
- https://datatracker.ietf.org/doc/html/rfc792
- https://medium.com/@gapple.web3/from-zero-to-ping-how-i-rebuilt-the-classic-network-tool-in-c-5f9ce447a291
- https://www.gnu.org/software/inetutils/manual/html_node/ping-invocation.html
- https://mmoumni.com/projects/ft_ping/
- https://github.com/vsteffen/ft_ping
