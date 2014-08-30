


Account = {balance = 0}
function Account.withdraw(self,a)
	self.balance = self.balance - a
end


--Account.withdraw(100)
print(Account.balance)

a=Account;
b=Account;
a.withdraw(a,20)   
b.withdraw(b,30)     -- will funciton on the same obj
--print("Account.balance", Account.balance)
print("a.balance",a.balance)
print("b.balance",b.balance)















