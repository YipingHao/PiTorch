#include <cmath>
#include <cstddef>
#include <cstdio>
#include <limits>
#include <vector>

extern "C" std::size_t pikachu_compute_input_count();
extern "C" std::size_t pikachu_compute_parameter_count();
extern "C" std::size_t pikachu_compute_output_count();
extern "C" void pikachu_compute(
    const double* input, const double* parameter, double* output);

int main()
{
    const std::size_t inputCount = pikachu_compute_input_count();
    const std::size_t parameterCount = pikachu_compute_parameter_count();
    const std::size_t outputCount = pikachu_compute_output_count();
    std::vector<double> input(inputCount, 0.0);
    std::vector<double> parameter(parameterCount, 0.0);
    std::vector<double> output(outputCount, std::numeric_limits<double>::quiet_NaN());

    for (std::size_t i = 0; i < inputCount; ++i)
        input[i] = 0.05 * static_cast<double>(i + 1);
    pikachu_compute(input.data(), parameter.data(), output.data());
    for (std::size_t i = 0; i < outputCount; ++i)
        if (output[i] != 0.0)
        {
            std::fprintf(stderr, "zero-parameter check failed at output %zu: %.17g\n", i, output[i]);
            return 1;
        }

    for (std::size_t i = 0; i < parameterCount; ++i)
        parameter[i] = 0.001 * static_cast<double>(1 + i % 17);
    pikachu_compute(input.data(), parameter.data(), output.data());
    for (std::size_t i = 0; i < outputCount; ++i)
        if (!std::isfinite(output[i]))
        {
            std::fprintf(stderr, "finite-value check failed at output %zu\n", i);
            return 2;
        }

    if (inputCount == 2 && parameterCount == 6 && outputCount == 2)
    {
        for (std::size_t i = 0; i < inputCount; ++i)
        {
            const double x = input[i];
            const double polynomial = parameter[0] + parameter[1] * x +
                parameter[2] * x * x + parameter[3] * x * x * x;
            const double z = x * parameter[4] + parameter[5];
            const double expected = polynomial * std::exp(-z * z);
            if (std::fabs(output[i] - expected) > 1.0e-14)
            {
                std::fprintf(stderr,
                    "parameterized-kernel check failed at output %zu: generated=%.17g expected=%.17g\n",
                    i, output[i], expected);
                return 4;
            }
        }
    }

    if (outputCount >= 1 + inputCount)
    {
        const std::vector<double> analytic = output;
        const double step = 1.0e-6;
        std::vector<double> plus(outputCount), minus(outputCount);
        for (std::size_t axis = 0; axis < inputCount; ++axis)
        {
            input[axis] += step;
            pikachu_compute(input.data(), parameter.data(), plus.data());
            input[axis] -= 2.0 * step;
            pikachu_compute(input.data(), parameter.data(), minus.data());
            input[axis] += step;
            const double numerical = (plus[0] - minus[0]) / (2.0 * step);
            const double exact = analytic[1 + axis];
            const double tolerance = 1.0e-7 * (1.0 + std::fabs(numerical));
            if (std::fabs(numerical - exact) > tolerance)
            {
                std::fprintf(stderr,
                    "gradient check failed at input %zu: analytic=%.17g numerical=%.17g\n",
                    axis, exact, numerical);
                return 3;
            }
        }
    }

    std::printf("tensor backend smoke test passed: input=%zu parameter=%zu output=%zu\n",
        inputCount, parameterCount, outputCount);
    return 0;
}
