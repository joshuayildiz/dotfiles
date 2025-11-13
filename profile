# My scripts & Plan 9 utils first
PATH=$home/work/dotfiles/bin:$PATH
PATH=$home/work/dotfiles/scripts:$PATH
PATH=/usr/local/plan9/bin:$PATH

# Homebrew
PATH=/opt/homebrew/bin:$PATH
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew

# Rust
if (test -d $home/.rustup) {
	PATH=$PATH:$home/.rustup/toolchains/stable-aarch64-apple-darwin/bin
	PATH=$PATH:$home/.cargo/bin
}

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
font=/mnt/font/BerkeleyMonoVariable-Regular/16a/font

# Plumber
if (! {ps -x | grep -q plumber}) {
	plumber
}

# Aliases

