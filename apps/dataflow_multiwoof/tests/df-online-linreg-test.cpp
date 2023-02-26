#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include <unistd.h>

void online_linreg_test() {
    add_node(1, 1, 1, LINREG); // Linear Regression node
    add_operand(1, 1, 2);      // x
    add_operand(1, 1, 3);      // y

    subscribe("1:1:0", "1:2");
    subscribe("1:1:1", "1:3");

    // Linear Regression Initialization

    int iters = 50;

    std::string data_woof = "laminar-1.linreg_data.1";
    woof_create(data_woof, sizeof(Regression), 100);

    setup();

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(-0.1, 0.1);

    std::vector<operand> x_values;
    std::vector<operand> y_values;

    for (int i = 0; i < iters; i++) {
        double x = i + distr(eng);
        double y = 3 + 2 * i + distr(eng);
        x_values.push_back(operand(x, i + 1));
        y_values.push_back(operand(y, i + 1));
    }

    for (int i = 0; i < iters; i++) {
        woof_put("laminar-1.output.2", "output_handler", &x_values[i]);
        woof_put("laminar-1.output.3", "output_handler", &y_values[i]);
        usleep(10000);
    }

    while (woof_last_seq("laminar-1.output.1") < iters) {
        sleep(1);
    }

    operand op;
    double result;
    woof_get("laminar-1.output.1", &op, 0);
    result = op.value;
    std::cout << "result: " << result << std::endl;
}

int main() {

    set_host(1);
    
    add_host(1, "169.231.235.168", "/home/centos/cspot/build/bin/");

    online_linreg_test();

    return 0;
}
