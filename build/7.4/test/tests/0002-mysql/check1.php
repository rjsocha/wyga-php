<?php
if(!extension_loaded('mysqli')) {
	echo "missing ext mysqli\n";
	exit(1);
}
if(!extension_loaded('pdo_mysql')) {
	echo "missing ext pdo_mysql\n";
	exit(1);
}
exit(0);
