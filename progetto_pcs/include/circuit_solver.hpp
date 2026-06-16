#pragma once

#include <map>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <optional>
#include "graph.hpp"       
#include "cycle_basis.hpp"  
#include "parser.hpp"

// Funzione principale che risolve il circuito assemblando il sistema lineare delle maglie
std::optional<std::map<std::string, double>> risolvi_circuito(const std::vector<Component>& componenti,
                                               const std::vector<OrientedCycle>& ciclo);