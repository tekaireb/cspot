#include "../dfinterface.h"

#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cmath>

#include <unistd.h>

void knn_test() {
    add_operand(1, 1, 1);      // K
    add_operand(1, 1, 2);      // x
    add_operand(1, 1, 3);      // y

    add_node(2, 1, 1, KNN);

    subscribe("2:1:0", "1:1");
    subscribe("2:1:1", "1:2");
    subscribe("2:1:2", "1:3");

    // KNN Initialization

    std::string knn_data_woof = "laminar-2.knn_data.1";
    woof_create(knn_data_woof, sizeof(Point), 25);

    std::vector<Point> points = {
        Point(1, 0, 0),  Point(1, 1, 0),  Point(0, 1, 0), Point(10, 10, 1),
        Point(9, 10, 1), Point(10, 9, 1), Point(9, 9, 1)};

    for (auto& p : points) {
        woof_put(knn_data_woof, "", &p);
    }

    setup(1);
    setup(2);
    sleep(1);

    int k = 3;
    Point p = Point(7, 8);

    operand op(k, 1);
    woof_put("laminar-1.output.1", "output_handler", &op);

    operand op2(p.x, 1);
    woof_put("laminar-1.output.2", "output_handler", &op2);

    operand op3(p.y, 1);
    woof_put("laminar-1.output.3", "output_handler", &op3);

    sleep(2);

    double result;
    woof_get("laminar-2.output.1", &op, 0);
    result = op.value;

    // Expected output: 1
    std::cout << "LABEL: " << result << std::endl;
}

int main() {

    set_host(1);
    add_host(1, "169.231.235.168", "/home/centos/cspot/build/bin/");

    knn_test();

    return 0;
}