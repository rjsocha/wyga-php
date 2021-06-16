ARG V
FROM wyga/php-ext-mysqli:${V} AS mysqli
FROM wyga/php-ext-pdo_mysql:${V} AS pdo_mysql
FROM wyga/php-ext-v8js:${V} AS v8js

FROM scratch AS build
COPY --from=mysqli / /
COPY --from=pdo_mysql / /
COPY --from=v8js / /

ARG V
FROM wyga/php:$V
COPY --from=build / /
RUN wyga-php-setup
COPY / /check/
