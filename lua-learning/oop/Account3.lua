


Account = {balance = 0}
function Account.withdraw(self,a)
	self.balance = self.balance - a
end


--Account.withdraw(100)
print(Account.balance)

a=Account;
b={ balance = 0, withdraw=Account.withdraw}		-- another obj ??
a.withdraw(a,20)   
b.withdraw(b,30)    
--print("Account.balance", Account.balance)
print("a.balance",a.balance)
print("b.balance",b.balance)















