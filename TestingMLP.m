function [RMSE] = TestingMLP(Input, nhiddenneurons, noutputs, netw)
    
    % nhiddenneurons - # of hidden neurons in a single hidden layer
    % noutputs - # of network outputs (# of output neurons)
    % netw - weights

    %Input is a matrix containing a test set;
    % Each row is a sample - inputs followed by a desired output
    A = Input;

    % N is now the number of learning samples
    % ninputs is now the number of inputs
    [N,ninputs]=size(A);
    ninputs=ninputs-1;

    % An array to store actual outputs after learning
    ActualOutputs = zeros(1, N);

    % N is now the number of learning samples
    % ninputs is now the number of inputs

    % extraction of input samples (only inputs)
    inputs=A(:,1:ninputs);
    % extraction of the desired outputs (assume that there is only 1 output
    % neuorn)
    targets=A(:,ninputs+1);

    % a for loop over all learning samples
    for j=1:N
             % calculation of the actual output of the network for the j-th
             % sample
             output  = EvalNN( inputs(j,:),netw,ninputs,nhiddenneurons,noutputs );
             % Accumulation of actual outputs
 
             %interpretation of output in the case of a binary output
             % any non-negative output --> 0.5
             % any negative output --> - 0.5
           %  if (output>=0) 
           %      output = 0.5;
           %  else
           %      output = -0.5;
           %  end
             
             ActualOutputs(j) = output;
             
    
             %disp([' Inputs [',num2str(inputs(j,:)), ' ] --> Actual Output:  [',num2str(output),']', '] --> Desired Output:  [',num2str(targets(j)),']'] )

    end
    % MSE over all testing samples
    error = sum((ActualOutputs - targets').^2)/N;
    % RMSE
    RMSE = sqrt(error);
    
    % test samples wherre errors occured
    Errors = (ActualOutputs ~= targets');
    
    % total number of test samples wherre errors occured
    NumOfErrors = sum(Errors);
    
    % Classification accuracy in % = 100% - %of errors
    Accuracy = 100 - ((NumOfErrors/N) * 100);
    
    disp (['Errors = ' num2str(NumOfErrors)]);
    disp (['Classification rate = ' num2str(Accuracy) '%' ]);
    
    
    figure (2);
    hold off
    plot(targets,'Or'); 
    hold on
    plot(ActualOutputs, '*b');
end