classdef Signal < mpt.Signal
%Bobcat.Signal  Class definition.

  methods
    function setupCoderInfo(h)
      % Use custom storage classes from this package
      useLocalCustomStorageClasses(h, 'Bobcat');
    end

    %---------------------------------------------------------------------------
    function h = Signal()
    end

  end % methods
end % classdef
