ARG V
FROM wyga/php-ext-imagick:${V}
FROM wyga/merge:1 AS merge
ARG V
FROM wyga/php-merge:$V
COPY / /check/
