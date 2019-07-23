# Fingertop
> Asynchronous is like Synchronous,Synchronous will be Asynchronous.

Fingertop is a framework which write with synchronous and execute in asynchronous.

Although callback programming based on event-driven models is very efficient, it requires a lot of skill for developers to deal with the call relations of those multi-layer functions. We hope to use the features of coroutines to improve the complexities of callback programming while ensuring event-driven high execution efficiency.

## Requirements
- libuv
- lua5.3
- ninja (Compile)

## Build
Clone source code from github.
```
$ git clone --recursive https://github.com/tiannian/Fingertop.git
```

Install Dependences. (for ArchLinux)
```
$ sudo pacman -S libuv lua ninja
```

Build Fingertop.
```
$ cd Fingertop
$ ninja
$ sudo ninja install
```

#### Static compile
If you want to static link library to Fingertop.
```
$ ninja -f static.ninja
```

## Reference
### Module timer
#### timer.new()
Create a instance of timer.

Return a timer instance.

#### timer:sleep(time)
Sleep this coroutine `time` milliseconds. This coroutine will be resume after `time` milliseconds.

### Module tcp
#### tcp.new()
Create a tcp socket instance to be server or client

Return a tcp socket instance.

#### tcp:bind(address,port)
Bind this socket in `address:port`

#### tcp:listen()


