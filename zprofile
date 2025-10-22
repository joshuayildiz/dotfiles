# Homebrew.
eval "$(/opt/homebrew/bin/brew shellenv)"

# Rust.
export PATH="$PATH:$HOME/.rustup/toolchains/stable-aarch64-apple-darwin/bin"
export PATH="$PATH:$HOME/.cargo/bin"

# Go.
export PATH="$PATH:$HOME/go/bin"

# Aliases.
alias l="ls -l"
