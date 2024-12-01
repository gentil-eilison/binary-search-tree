FROM gcc:11.4.0

WORKDIR /app

COPY ./main.cpp /app

RUN mkdir /app/output
RUN g++ -Wall -Wextra -g3 --std=c++20 /app/main.cpp -o /app/output/main

CMD ["/app/output/main"]