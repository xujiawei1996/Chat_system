#!/bin/bash

ROOT_PATH=$(pwd)
BIN=$ROOT_PATH/chat_system
CONF=$ROOT_PATH/conf/server.conf
pid=''

proc=$(basename $0)

function usage()
{
	printf "%s %s\n" "proc" "[start(-s)] | [stop(-t)] | [restart(-rt)] | [status(-a)]"
}

function check_status()
{
	name=$(basename $BIN)
	pid=$(pidof $name)
	if [ ! -z "$pid" ];then
		return 0
	else
		return 1
	fi
}

function server_start()
{
	if check_status;then
			echo "the proc is runing"
	else
			ip=$(awk -F: '/^IP/{print $NF}' $CONF)
			port=$(awk -F: '/^PORT/{print $NF}' $CONF)
			$BIN $ip $port
			echo "server is starting...done"
	fi
}

function server_stop()
{
	if check_status;then
		kill -9 $pid
		echo "server stop...done"
	else
		echo "server is not runing"
	fi
}

function server_restart()
{
	server_stop
	server_start
}

function status()
{
	if check_status;then
		echo "server is runing..pid is : $pid"
	else
		echo "server is not running..."
	fi
}

if [ $# -ne 1 ];then
	usage
	exit 1
fi

case $1 in
	start | -s)
		server_start
	;;
	stop | -t)
		server_stop
	;;
	restart | -rt)
		server_restart
	;;
	status | -a)
		check_status	
	;;
	* )
	usage
	exit 2
esac

