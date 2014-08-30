


Account = {balance = 0}
function Account.withdraw(a)
	Account.balance = Account.balance - a
end


Account.withdraw(100)
print(Account.balance)

a=Account;Account=nil
-- a.withdraw()    -- error

















