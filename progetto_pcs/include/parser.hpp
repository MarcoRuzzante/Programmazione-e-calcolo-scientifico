#pragma once
#include <vector>
#include <string>
#include <optional>
#include "Component.hpp"

// Funzione che legge il file di netlist e restituisce il vettore dei componenti estratti
std::optional<std::vector<Component>> leggi_netlist(const std::string& nome_file);