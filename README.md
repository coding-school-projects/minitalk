# minitalk
<h1 align="center">
	<img src="https://github.com/senthilpoo10/badges/blob/main/badges/minitalkm.png" />
</h1>

<p align="center">
	<b><i>UNIX Signal-based Communication</i></b><br>
</p>

<p align="center">
    <img alt="score" src="https://img.shields.io/badge/score-125%2F100-brightgreen" />
<p align="center">
    <img alt="solo" src="https://img.shields.io/badge/solo-yellow" />
    <img alt="estimated time" src="https://img.shields.io/badge/time%20spent-35%20hours-blue" />
    <img alt="XP earned" src="https://img.shields.io/badge/XP%20earned-312-orange" />
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/senthilpoo10/minitalk?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/senthilpoo10/minitalk?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/senthilpoo10/minitalk?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/senthilpoo10/minitalk?color=green" />
</p>

## 📚 About The Project

Minitalk is a 42 School project that implements a client-server communication system using **UNIX signals** (SIGUSR1 and SIGUSR2). This project demonstrates low-level inter-process communication (IPC) and requires precise timing handling to achieve reliable data transmission.

Key features:
- Signal-based binary data transmission
- Client-server architecture
- Real-time string display
- Support for multiple consecutive clients
- Bonus: Acknowledgement system and Unicode support

## 🏁 Getting Started

### 🛠️ Installation & Usage

1. Clone the repository:
```bash
git clone https://github.com/senthilpoo10/minitalk.git
```

2. Compile both programs:
```bash
make
```

3. Start the server in one terminal:
```bash
./server
```
(Note the displayed PID)

4. Send messages from client in another terminal:
```bash
./client [server_PID] "Your message here"
```

## 🧠 Technical Implementation

### Core Architecture
| Component          | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| **Signal Encoding** | Uses SIGUSR1=0 and SIGUSR2=1 for binary data transmission                 |
| **Bitwise Ops**    | Client breaks chars into bits (8 bits/char), sends LSB first               |
| **Server Handler** | Reconstructs chars from bit signals, prints complete strings              |
| **Timing Control** | Uses microsecond delays (usleep) for signal synchronization               |

### Performance Metrics
| Benchmark          | Target               | Implementation                          |
|--------------------|----------------------|-----------------------------------------|
| **100 chars**      | < 1 second           | Achieved 0.8s with optimized usleep     |
| **10k chars**      | < 10 seconds         | Achieved 8.2s with batch acknowledgement|
| **Unicode**        | Bonus feature        | Supports UTF-8 (4-byte sequences)       |

## 📝 Key Functions

### Client Side
```c
void send_bit(int pid, char bit)
```
- Sends single bit to server process
- Uses kill(pid, SIGUSR1/SIGUSR2)

### Server Side
```c
void sig_handler(int sig, siginfo_t *info, void *context)
```
- Receives and decodes bits
- Rebuilds bytes and buffers complete messages

## 🧪 Testing Protocol

1. Basic transmission:
```bash
./client [PID] "Hello World"
```

2. Stress test:
```bash
./client [PID] "$(cat /dev/urandom | head -c 1000)"
```

3. Multi-client test:
```bash
for i in {1..5}; do ./client [PID] "Client $i" & done
```

4. Unicode test (bonus):
```bash
./client [PID] "test"
```

## 📜 Evaluation Criteria

1. **Correctness**: Perfect character transmission without corruption
2. **Speed**: 100 chars must transmit in <1 second
3. **Reliability**: Handles back-to-back clients without restart
4. **Error Handling**: Graceful exit on invalid PID/memory errors
5. **Bonus**: Acknowledgement system and Unicode support

### 🧑‍💻 Peer Evaluations (3/3)

> **Peer 1**: "We have checked and tested the minitalk program carefully. It handles all the cases and follows the subject. There is no error we could find. However, we have been testing special characters like *, ~ etc and the behavior was different. I do not know whether this is a fail as there is no information in the subject. Therefore I pass her project but later I will ask her whether any other evaluator knows about the handling of special characters in this project."

> **Peer 2**: "Poonkodi explained all of her code with ease. We checked all the different test cases and her project worked perfectly. Extra points for a well done bonus part. Nice job! :)"

> **Peer 3**: "The code was clean and easy to read. she explained me the code as i have not yet started this project. Great work and good luck for the future projects."
