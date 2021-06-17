ARG V
FROM wyga/php-ext-mysqli:${V}
FROM wyga/php-ext-pdo_mysql:${V}
FROM wyga/php-ext-gd:${V}
FROM wyga/merge:3 AS merge
ARG V
FROM wyga/php-merge:$V
COPY / /check/
