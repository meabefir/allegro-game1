#pragma once

void print_bits(int x) {
	for (int i = 31; i >= 0; i--) {
		if ((1 << i) & x)
			std::cout << 1;
		else
			std::cout << 0;
	}
	std::cout << '\n';
}
