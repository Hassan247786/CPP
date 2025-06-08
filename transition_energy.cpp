// Description: This program calculates the transition energy between electron energy levels,
// or equivalently, the energy of emitted photons in such transitions - according to the Bohr Model.
// Author: Hassan Hashmi
// Date: 06/02/2024
#include <iostream>

#include <cmath>

#include <limits>

const double rydberg_energy = 13.6;
const double electronvolt_to_joule_factor = 1.602e-19;
double transition_energy(int atomic_number, int n_initial, int n_final) {
  return rydberg_energy * pow(atomic_number, 2) * (1.0 / pow(n_final, 2) - 1.0 / pow(n_initial, 2));
}
int validate_user_input(const std::string & prompt, int minimum, int maximum) {
  int user_value;
  while (true) {
    std::cout << prompt;
    std::cin >> user_value;
    if (!std::cin.fail() && user_value >= minimum && user_value <= maximum && std::cin.peek() == '\n')
      break;
    else {
      std::cout << "Sorry, your input was not valid.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
    }
  }
  return user_value;
}
int main() {
  int proton_number, n_initial, n_final;
  char energy_unit, repeat;
  do {
    proton_number = validate_user_input("Enter the atomic number (1-118): ", 1, 118);
    do {
      n_initial = validate_user_input("Enter the initial quantum number: ", 1, 10000);
      n_final = validate_user_input("Enter the final quantum number: ", 1, 10000);
      if (n_initial < n_final)
        std::cout << "Error. The initial energy level cannot be lower than the final energy level for photon emission. Please try again.\n";
      else if (n_initial == n_final) {
        std::cout << "There is no photon emission. The transition energy is zero.\n";
        return 0;
      }
    }
    while (n_initial <= n_final);
    double energy = transition_energy(proton_number, n_initial, n_final);
    energy_unit = validate_user_input("Would you like your answer in joules or electron volts? Enter 1 for J, 2 for eV: ", 1, 2);
    if (energy_unit == 1) {
      energy *= electronvolt_to_joule_factor;
      std::cout.precision(3);
      std::cout << "The energy of the transition is: " << energy << " Joules\n";
    } else if (energy_unit == 2) {
      std::cout.precision(3);
      std::cout << "The energy of the transition is: " << energy << " eV\n";
    }
    repeat = validate_user_input("Would you like to calculate another transition? (1 for yes, 2 for no): ", 1, 2);
  }
  while (repeat == 1);
  return 0;
}