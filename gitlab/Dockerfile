FROM alpine:3.14

RUN apk add make g++

WORKDIR /app
COPY . . 
RUN make

FROM alpine:3.14

RUN apk add libstdc++ git bash

COPY --from=0 /app/impactdoc /bin/impactdoc
COPY --from=0 /app/gitlab/check.sh /opt/check.sh
