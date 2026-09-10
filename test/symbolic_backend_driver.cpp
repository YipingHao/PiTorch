#include <cmath>
#include <iostream>

extern "C" void pikachu_symbolic_kernel(
	const double* const* input, const double* parameter, double* output);
extern "C" void pikachu_symbolic_kernel_miniop(
	const double* const* input, const double* parameter, double* output);

int main()
{
	double inputGroup0[2] = { 0.37, -0.21 };
	double inputGroup1[1] = { 0.43 };
	const double* inputs[2] = { inputGroup0, inputGroup1 };
	double parameters[1] = { 1.25 };
	double outputs[4] = { 0.0, 0.0, 0.0, 0.0 };
	double outputsMiniOp[4] = { 0.0, 0.0, 0.0, 0.0 };
	pikachu_symbolic_kernel(inputs, parameters, outputs);
	pikachu_symbolic_kernel_miniop(inputs, parameters, outputsMiniOp);

	const double expected0 = (std::sin(inputGroup0[0]) + std::cos(inputGroup0[1])) *
		std::exp(-inputGroup1[0]);
	const double expected1 = std::pow(inputGroup0[0] + parameters[0], 2.0) /
		std::sqrt(4.0) - std::log(parameters[0] + 2.0);
	if (std::fabs(outputs[0] - expected0) >= 1.0e-12 ||
		std::fabs(outputs[1] - expected1) >= 1.0e-12 ||
		!std::isnan(outputs[2]) || !std::isinf(outputs[3]) || outputs[3] < 0.0)
	{
		std::cerr << "generated backend mismatch: " << outputs[0] << ", "
			<< outputs[1] << std::endl;
		return 1;
	}
	for (size_t i = 0; i < 4; ++i)
	{
		if ((std::isnan(outputs[i]) && std::isnan(outputsMiniOp[i])) ||
			outputs[i] == outputsMiniOp[i]) continue;
		std::cerr << "MiniOp/MiniReg mismatch at output " << i << std::endl;
		return 2;
	}
	std::cout << "generated C++ backend matches the analytic reference." << std::endl;
	return 0;
}
