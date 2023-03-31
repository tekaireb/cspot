//
// Created by lukas on 20.03.2023.
//
#include "df_machine_learning.h"

#include "../df_interface.h"
#include "../logger_system/df_operation_logger.h"

#include <queue>

// Struct to hold each data point. Includes coordinates (x, y) and class (label)
struct Point {
    double x;
    double y;
    int label;

    explicit Point(double x = 0.0, double y = 0.0, int label = -1) : x(x), y(y), label(label) {}
};

// Struct to hold / perform online linear regression
struct Regression {
    double num;
    double x;
    double y;
    double xx;
    double xy;
    double slope;
    double intercept;

    explicit Regression(double x = 0, double y = 0, double xx = 0, double xy = 0,
                        double slope = 0, double intercept = 0)
            : x(x), y(y), xx(xx), xy(xy), slope(slope), intercept(intercept) {
        num = 0.0;
    }

    void update(double new_x, double new_y) {
        double dt = 1e-2;   // Time step (delta t)
        double T = 5e-2;    // Time constant
        double decay_factor = exp(-dt / T);

        // Decay values
        num *= decay_factor;
        x *= decay_factor;
        y *= decay_factor;
        xx *= decay_factor;
        xy *= decay_factor;

        // Add new datapoint
        num += 1;
        x += new_x;
        y += new_y;
        xx += new_x * new_x;
        xy += new_x * new_y;

        // Calculate determinant and new slope / intercept
        double det = num * xx - pow(x, 2);
        if (det > 1e-10) {
            intercept = (xx * y - xy * x) / det;
            slope = (xy * num - x * y) / det;
        }
    }
};

// Helper function to calculate Euclidean distance between two points
double dist(Point& a, Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


//int compute_knn(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE *result);

//int compute_linreg(const DF_VALUE operands[], unsigned int operand_count, DF_TYPE result_type, DF_VALUE *result);


int df_machine_learning_operation(const DF_MACHINE_LEARNING_OP machine_learning_operation,
                                  const DF_VALUE operands[],
                                  const unsigned int operand_count,
                                  DF_VALUE *result) {
    // TODO
    return 0;
}

int df_machine_learning_operation_with_type(const DF_MACHINE_LEARNING_OP machine_learning_operation,
                                            const DF_VALUE operands[],
                                            const unsigned int operand_count,
                                            const DF_TYPE result_type,
                                            DF_VALUE *result) {
    /*
    switch (machine_learning_operation) {
        case DF_MACHINE_LEARNING_KNN: {
            if (operand_count != 1) {
                log_value_count_mismatch(1, operand_count);
                return 0;
            }
            return compute_knn(operands[0], result);
        }
        case DF_MACHINE_LEARNING_LINREG:
            return compute_linreg(operands, operand_count, result_type, result);
        default:
            log_operation_not_existing("MACHINE_LEARNING", machine_learning_operation);
            return 0;
    }
     */
    return 0;
}

/*

int compute_knn(const DF_VALUE operands[],
                const unsigned int operand_count,
                const DF_TYPE result_type,
                DF_VALUE *result) {
    size_t k = static_cast<size_t>(operands[0].value);
    Point p = Point(ops[1].value, ops[2].value);
    std::string data_woof = "laminar-" + std::to_string(ns) + ".knn_data." + std::to_string(n.id);

    using distPair = std::pair<double, int>; // (distance, label)
    std::priority_queue<distPair, std::vector<distPair>, std::greater<distPair>> pq;

    // Iterate over points data and add to priority queue
    unsigned long last_seq = woof_last_seq(data_woof);
    Point p_i;
    for (unsigned long s = 0; s <= last_seq; s++) {
        woof_get(data_woof, &p_i, s);
        double d = dist(p, p_i);
        pq.push(std::make_pair(d, p_i.label));
    }

    // Pop top k elements and find most common label
    int num_pops = std::min(k, pq.size());
    int most_common_label = pq.top().second;
    int count = 1;
    pq.pop();
    for (int i = 1; i < num_pops; i++) {
        if (pq.top().second == most_common_label)
            count++;
        else
            count--;

        if (count == 0) {
            most_common_label = pq.top().second;
            count = 1;
        }
        pq.pop();
    }

    // Add result to data woof
    p.label = most_common_label;
    woof_put(data_woof, "", &p);

    result.value = most_common_label;
}

int compute_linreg(const DF_VALUE operands[],
                   unsigned int operand_count,
                   DF_TYPE result_type,
                   DF_VALUE *result) {
    std::string data_woof = "laminar-" + std::to_string(ns) + ".linreg_data." + std::to_string(n.id);

    Regression r;
    if (woof_last_seq(data_woof)) {
        woof_get(data_woof, &r, 0);
    }
    r.update(ops[0].value, ops[1].value);
    woof_put(data_woof, "", &r);
    result.value = r.slope;
}
 */