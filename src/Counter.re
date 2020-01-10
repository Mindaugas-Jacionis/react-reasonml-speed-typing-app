type state = {
  time: int,
  timerId: option(Js.Global.intervalId),
};

type retainedProps = {shouldCount: bool};

type action =
  | SetTimer(Js.Global.intervalId)
  | Tick;

let clearInterval = id =>
  switch (id) {
  | None => ()
  | Some(id) => Js.Global.clearInterval(id)
  };

let component = ReasonReact.reducerComponentWithRetainedProps("Counter");

let make = (~onFinish, ~initialTime=60, ~shouldCount=true, _children) => {
  ...component,

  initialState: () => {time: initialTime, timerId: None},

  reducer: action =>
    switch (action) {
    | SetTimer(timerId) => (
        state => ReasonReact.Update({...state, timerId: Some(timerId)})
      )
    | Tick => (
        state => {
          let updatedTime = state.time - 1;

          if (updatedTime == 0) {
            clearInterval(state.timerId);
            onFinish();
          };

          ReasonReact.Update({...state, time: updatedTime});
        }
      )
    },

  didMount: ({send}) =>
    if (shouldCount) {
      let intervalId = Js.Global.setInterval(() => send(Tick), 1000);
      send(SetTimer(intervalId));
    },

  retainedProps: {
    shouldCount: shouldCount,
  },
  didUpdate: ({oldSelf, newSelf}) =>
    if (oldSelf.retainedProps.shouldCount !== newSelf.retainedProps.shouldCount
        && newSelf.retainedProps.shouldCount) {
      let intervalId = Js.Global.setInterval(() => newSelf.send(Tick), 1000);
      newSelf.send(SetTimer(intervalId));
    },

  willUnmount: ({state: {timerId}}) => clearInterval(timerId),

  render: ({state: {time}}) =>
    <div> {ReasonReact.string("Time left: " ++ string_of_int(time))} </div>,
};