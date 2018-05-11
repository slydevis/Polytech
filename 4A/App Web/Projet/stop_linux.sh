#!/bin/bash

RED='\033[0;31m'
GREEN="\033[0;32m"
NC='\033[0m' 

echo -e "${RED}Killing all node process${NC}"
killall -KILL node