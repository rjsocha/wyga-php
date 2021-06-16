<?php
if(!extension_loaded('memcached')) {
	echo "missing ext memcached\n";
	exit(1);
}
exit(0);
