function desinflar(obj, millispadesinflar)
	string2send = "w,1,";
    for i = 1:9
        string2send = string2send + ',' + num2str(-millispadesinflar) ;
    end
    writeline(obj, string2send);
    

end