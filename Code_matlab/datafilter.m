function [data_filtered] = datafilter(data)


j = 1;
data_filtered.p = 1;


for i = 1:data.nummuestras
    
    if data.outputs.green(i, 1) > 400 
        continue

    end
    if data.outputs.green(i, 2) > 400 
        continue
    end
    if data.outputs.green(i, 3) > 800 
        continue
        
    else
        data_filtered.outputs.green(j, :) = data.outputs.green(i, :);
        data_filtered.outputs.blue(j, :) = data.outputs.blue(i, :);
        data_filtered.inputs(j,:) = data.inputs(i, :);
        j = j+ 1;

    end



end