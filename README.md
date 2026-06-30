# webserv

**webserv** is a 42 project — a single-threaded, non-blocking HTTP/1.1 web server written in C++98, built on top of Linux's `epoll` for efficient I/O multiplexing.

## ⚙️ Features

- HTTP/1.1 request handling (GET, POST, DELETE)
- Custom configuration file syntax for:
  - Multiple server blocks on distinct ports
  - Per-location configuration (root, alias, methods, redirections)
  - Custom error pages per status code
- Static file serving with MIME type detection (`mime.types`)
- CGI execution with configurable interpreters per file extension (`.sh`, `.py`, `.php`, ...)
- Non-blocking I/O event loop using `epoll(2)`
- Finite state machine for HTTP request parsing
- Chunked transfer encoding (including trailers)
- Cookie-based session management with timeout
- Request timeout detection (408) and body/header size limits
- Autoindex: directory listing when no index file is found
- File upload via POST with configurable target directory
- Redirections via `return STATUS URL` directive
- Load testing setup with `siege` (10 concurrent clients)
- Shell-based test suite for bad request validation (duplicate headers, missing Host, etc.)

## 🧠 Learning Objectives

- Deep understanding of the HTTP/1.1 protocol: request/response format, status codes, headers
- Socket programming: TCP/IP lifecycle, `bind`/`listen`/`accept`, non-blocking I/O
- Event-driven architecture with `epoll`: managing clients, CGI pipes, and stdin in a single loop
- Writing a finite state machine for robust incremental HTTP parsing
- Implementing the CGI/1.1 protocol: forking child processes, environment variable passing, pipe communication
- Parsing and validating a custom configuration language (tokenizer + directive parser)
- Session handling and connection lifecycle management (Keep-Alive, timeouts)
- Building a modular C++ codebase under strict C++98 constraints (-Wall -Wextra -Werror)

## 🚀 Usage

```bash
make build
./code/WebServ [config_file]   # defaults to configs/multipleServers.conf
```

Config files are in `configs/`. The server can be stopped by pressing Enter on stdin.

## 📄 Configuration

```nginx
server {
    listen 8080;

    location / {
        root ./www/default;
        allow_methods GET POST DELETE;
        post_directory ./www/default/post/;
        client_max_body_size 3000000;
        autoindex on;
        index index.html;
        error_page 404 /404.html;
    }

    location /cgi-bin {
        root ./www/default/;
        cgi .sh;
        cgi .py /usr/bin/python3;
    }

    location /old {
        return 301 /new;
    }
}
```

| Directive | Purpose |
|-----------|---------|
| `listen PORT` | Port to bind (default 8080) |
| `root PATH` | Base directory for serving files |
| `alias PATH` | Replace location prefix in resolved path |
| `allow_methods` | Whitelist of HTTP methods |
| `client_max_body_size` | Max POST body in bytes |
| `client_max_header_size` | Max header block in bytes |
| `autoindex on/off` | Directory listing |
| `index FILE` | Default file for directory requests |
| `post_directory PATH` | Where POST uploads are saved |
| `cgi .EXT [/path/bin]` | CGI handler for a file extension |
| `return CODE URL` | HTTP redirect |
| `error_page CODE /path` | Custom error page |

## 🛠️ Makefile targets

| Target | Action |
|--------|--------|
| `make build` | Compile the binary (parallel) |
| `make run` | Run with `configs/default.conf` |
| `make run_multiple` | Run with `configs/multipleServers.conf` |
| `make debug` | Run under Valgrind |
| `make debugLeaks` | Full leak check with Valgrind |
| `make siege_run` / `make siege_test` | Load test (10 clients × 10 s) |

---

Compiled with `c++` `-Wall -Wextra -Werror -std=c++98 -g3` on Linux x86_64.
