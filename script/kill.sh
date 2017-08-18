#!/bin/bash
pid=`ps -ef | grep "tick" | grep -v "grep" | awk '{print $2}'`
kill -2 $pid
