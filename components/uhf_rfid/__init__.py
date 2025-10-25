# components/uhf_rfid/__init__.py
import esphome.codegen as cg

# Create the namespace and a forward-declared class symbol
uhf_ns = cg.esphome_ns.namespace("uhf_rfid")
UhfRfid = uhf_ns.class_("UhfRfid")  # forward-declare the type for main.cpp
