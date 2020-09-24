--Anthony Bartman
--Lab 2
--Dr. Livingston
--Summary:
--This creates a custom hardware system that will rotate a motor to a certain degree from
--its starting position based on a 20ms pulse from the 50MHz clock of the DE-10 Lite

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

--This entity controls how the SERVO hardware will function by using
--the DE-10 Lite switches to determine the correct amount of EN
--to send to the motor
entity SERVO is
port(
			CLK : in std_logic; 
			DATA : in std_logic_vector(7 downto 0); -- Used to send SERVOs a consistent pulse to stay at a position
			EN: out std_logic --Tells the SERVO to move, sends pulse to motors
		   );
end entity SERVO;

--This behavioral architecture controls how and when to send the pulse to the SERVO motors based
--on a free running counter. The SERVO motor will get a pulse every 20ms and based on the DE-10's
--50MHz clock, the motor will rotate if a value the of the slider switchs are in between 0 and 200.
architecture Behavioral of SERVO is
				
	signal cnt: integer range 0 to 1000000; --Used to count 20ms w/ 50Mhz CLK
	signal input: integer := 0; --Used to determine values of the slider switches
	
	--assign pins 
--	attribute chip_pin: string;
--	attribute chip_pin of CLK: signal is "P11";
--	attribute chip_pin of EN: signal is "AA17,AB19"; --Arduino IO9 and I010
-- attribute chip_pin of DATA: signal is "A14, A13, B12, A12, C12, D12, C11, C10";

begin
--This process is used to control the free-running counter that will move and reset SERVOs 
	counter: process(CLK)
		begin
		if (rising_edge(CLK)) then
			if(cnt = 1000000) then
				cnt <= 0;
			else
			 cnt <= cnt+1;
			end if;
		end if;
	end process; 
	
--This process handles when the counter changes, this will determine what
--to do to the motors based on the counter and its inputted switch delay
--0:  pulse width = 1 ms
--100:  pulse width = 1.5 ms
--200:  pulse width = 2 ms
--201 to 255:  no output, output remains low at all times
	OUTPUT: process(cnt, DATA) is	
	begin
	
		input <= to_integer(unsigned((DATA)));
		
		if(input > 200) then
			EN <= '0';
		elsif(cnt >= (input * (500/2)) + 50000) then
			EN <= '0';
		else
			EN <= '1';
		end if;
	
	end process OUTPUT;

end architecture Behavioral;