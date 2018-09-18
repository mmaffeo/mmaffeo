classdef Parameter < mpt.Parameter
%Bobcat.Parameter  Class definition.

  methods
    function setupCoderInfo(h)
      % Use custom storage classes from this package
      useLocalCustomStorageClasses(h, 'Bobcat');
    end

    %---------------------------------------------------------------------------
    function h = Parameter()
    end

  end % methods
end % classdef
