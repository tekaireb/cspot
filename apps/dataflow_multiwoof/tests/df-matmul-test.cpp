#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <vector>

#include <unistd.h>


void mat_test(const std::vector<std::vector<double>>& a,
              const std::vector<std::vector<double>>& b) {
    
    std::ofstream out("test.txt");

    int rows_a = a.size();
    int cols_a = a[0].size();
    int rows_b = b.size();
    int cols_b = b[0].size();

    // Result matrix dimensions    
    int rows_r = a.size();
    int cols_r = b[0].size();

    // Create operands
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            add_operand(1, 0, i * cols_a + j + 1);
        }
    }

    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            add_operand(2, 0, i * cols_b + j + 1);
        }
    }

    int id;
    for (int r = 0; r < rows_r; r++) {
        for (int c = 0; c < cols_r; c++) {
            // Create addition node for intermediate products
            add_node(4, 0, r * cols_r + c + 1, ADD);

            // Create all multiplication nodes for one output cell
            for (int i = 0; i < cols_a; i++) {
                id = r * (cols_r * cols_a) + c * cols_a + i + 1;
                add_node(3, 0, id, MUL);
                subscribe(3, id, 0, 1, r * cols_a + i + 1);
                subscribe(3, id, 1, 2, i * cols_b + c + 1);

                // Connect product to be summed
                subscribe(4, r * cols_r + c + 1, i, 3, id);
            }
        }
    }
    
    /* Run program */

    setup();

    sleep(1);

    // Write matrices to operands
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            operand op(a[i][j], 1);
            id = i * cols_a + j + 1;
            woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, id), OUTPUT_HANDLER, &op);
        }
    }

    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            operand op(b[i][j], 1);
            id = i * cols_b + j + 1;
            woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, id), OUTPUT_HANDLER, &op);
        }
    }    

    sleep(3);

    operand op;
    std::vector<std::vector<double>> v;
    for (int r = 0; r < rows_r; r++) {
        v.push_back({});
        for (int c = 0; c < cols_r; c++) {
            id = r * cols_r + c + 1;
            woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, 4, id), &op, 1);
            v[r].push_back(op.value);
        }
    }

    std::cout << "OUTPUTS:" << std::endl;
    for (auto& row : v) {
        for (auto& i : row) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

int main() {

    set_host(0);
    
    add_host(0, "169.231.235.168", "/home/centos/cspot/build/bin/");

    std::vector<std::vector<double>> a = {
        {1, 2, 3},
        {4, 5, 6}
    };

    std::vector<std::vector<double>> b = {
        {10, 11},
        {20, 21},
        {30, 31}
    };
    
    // 140 146 
    // 320 335

    mat_test(a, b);

    return 0;
}

