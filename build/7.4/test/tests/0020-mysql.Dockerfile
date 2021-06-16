ARG V
FROM wyga/php-ext-mysqli:${V} AS mysqli
FROM wyga/php-ext-pdo_mysql:${V} AS pdo_mysql

FROM scratch AS build
COPY --from=mysqli / /
COPY --from=pdo_mysql / /

ARG V
FROM wyga/php:$V
COPY --from=build / /
RUN wyga-php-setup
COPY / /check/
