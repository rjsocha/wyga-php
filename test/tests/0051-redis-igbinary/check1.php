<?php
$ext="redis";
if(!extension_loaded($ext)) {
	echo "missing ext $ext\n";
	exit(1);
}
exit(0);
