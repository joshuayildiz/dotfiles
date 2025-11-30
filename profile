# My scripts & Plan 9 utils first
PATH=/usr/local/plan9/bin:$PATH
PATH=$home/work/dotfiles/scripts:$PATH
PATH=$home/work/dotfiles/bin:$PATH

# Homebrew
PATH=/opt/homebrew/bin:$PATH
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew

# Python
PATH=$PATH:$home/Library/Python/3.9/bin

# Rust
if (test -d $home/.rustup) {
	PATH=$PATH:$home/.rustup/toolchains/stable-aarch64-apple-darwin/bin
	PATH=$PATH:$home/.cargo/bin
}

# Go
PATH=$PATH:$home/go/bin

# Postgres
PATH=$PATH:/Applications/Postgres.app/Contents/Versions/latest/bin

# Namespace
if (~ $#user 0) {
	user=`{whoami}
}
if (~ $#DISPLAY 0) {
	DISPLAY=:0
}
NAMESPACE=/tmp/ns.$user.$DISPLAY
mkdir -p $NAMESPACE

# Font
if (! {ps -x | grep -q fontsrv}) {
	fontsrv &
}
font=/mnt/font/BerkeleyMonoVariable-Regular/14a/font

# Plumber
if (! {ps -x | grep -q plumber}) {
	plumber
}

# Aliases

