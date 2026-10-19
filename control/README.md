\#control/README.md





\# AUROUAV Control Module



Implements hierarchical control:



\- MPC trajectory optimization

\- RL steering prior (Gaussian PDF)

\- PX4 offboard control



\### Nodes

\- mpc\_node

\- rl\_prior\_node

\- px4\_bridge\_node



\### Outputs

\- /mavros/setpoint\_raw/local

\- /auro\_uav/control\_cmd



