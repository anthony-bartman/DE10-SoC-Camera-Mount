--Anthony Bartman
--Lab 6
--Dr. Livingston
--Summary:
--This creates a testbench to simulate the servo file

library ieee;
use ieee.std_logic_1164.all;

entity testbench is
end entity testbench;

--This dataflow architecture
architecture DATAFLOW of testbench is

	signal CLK: std_logic;
	signal EN: std_logic;
	signal DATA: std_logic_vector(7 downto 0):= "00000000";

	begin
	UUT:entity work.servo port map(CLK=>CLK, EN=>EN, DATA=>DATA);
	
		clock:process
			begin
				CLK <= '1'; wait for 1ns;
				CLK <= '0'; wait for 1ns;
		end process clock;
		
		DATA <= "11110000" after 20ms;
		
end architecture DATAFLOW;