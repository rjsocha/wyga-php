ARG V
FROM wyga/php-ext-memcached:${V}
FROM wyga/merge:1 AS merge
ARG V
FROM wyga/php-merge:$V
COPY / /check/
