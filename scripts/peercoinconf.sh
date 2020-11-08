#!/bin/bash -ev

mkdir -p ~/.slimcoin
echo "rpcuser=username" >>~/.slimcoin/slimcoin.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >>~/.slimcoin/slimcoin.conf

