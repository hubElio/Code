----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/25/2023 02:25:49 PM
-- Design Name: 
-- Module Name: ADD_2bits - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ADD_2bits is
    Port ( A : in STD_LOGIC;
           B : in STD_LOGIC;
           Ci : in STD_LOGIC;
           Co : out STD_LOGIC;
           S : out STD_LOGIC);
end ADD_2bits;

architecture Behavioral of ADD_2bits is

begin

S <= (not(A) and ((not(B) and Ci) or (B and not(Ci)))) or (A and ((B and Ci) or (not(B) and not(Ci))));

Co <= (B and Ci) or (A and Ci) or (A and B);

end Behavioral;
