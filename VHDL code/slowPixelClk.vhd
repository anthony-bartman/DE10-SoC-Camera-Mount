--Anthony Bartman
--Lab 5
--Dr. Livingston
--Summary:
--This creates a a slow clock that will be used for the pixel clock 

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

--This entity controls how the main clock will be slowed down so the camera can read
--and write to pixels properly
entity PIXELCLK is
	port(
			CLK : in std_logic; 
			SL_CLK: out std_logic --Outputs the slow clock rate for pixel clock
		   );
end entity PIXELCLK;

--This behavioral architecture will take in the main clock input, and change the speed to
--25 Mhz clock instead of the 50 Mhz clock
architecture Behavioral of PIXELCLK is
				
	signal cnt: integer := 0; --Used for determining half of the clock speed

begin
--This process is used to slow down the clock by outputting a 25 Mhz clock instead of a 50 Mhz clock
	slowClock: process(CLK)
		begin
		if (rising_edge(CLK)) then
			if(cnt = 0) then
				cnt <= 1;
				SL_CLK <= '0';
			else -- cnt = '1'
				cnt <= 0;
				SL_CLK <= '1';
			end if;
		end if;
	end process; 

end architecture Behavioral;

